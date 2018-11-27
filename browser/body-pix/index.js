/**
 * @license
 * Copyright 2018 Google Inc. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * =============================================================================
 */
// import * as personSegmentation from '@tensorflow-models/body-pix';
// import dat from 'dat.gui';
// import Stats from 'stats.js';

// import * as partColorScales from './part_color_scales';
var partColorScales = [];
partColorScales.push(rainbow);
partColorScales.push(warm);
partColorScales.push(spectral);


var rhi, ghi, bhi;
var rlo, glo, blo;

function setTarget(r, g, b, range) {
  range = range || 32;
  rhi = r + range, rlo = r - range;
  ghi = g + range, glo = g - range;
  bhi = b + range, blo = b - range;
}

const stats = new Stats();
const videoWidth = 640;
const videoHeight = 480;

function isAndroid() {
  return /Android/i.test(navigator.userAgent);
}

function isiOS() {
  return /iPhone|iPad|iPod/i.test(navigator.userAgent);
}

function isMobile() {
  return isAndroid() || isiOS();
}

/**
 * Loads a the camera to be used in the demo
 *
 */
async function setupCamera() {
  if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) {
    throw new Error(
      'Browser API navigator.mediaDevices.getUserMedia not available');
  }

  const video = document.getElementById('video');
  video.width = videoWidth;
  video.height = videoHeight;

  const mobile = isMobile();
  const stream = await navigator.mediaDevices.getUserMedia({
    'audio': false,
    'video': {
      facingMode: 'user',
      width: mobile ? undefined : videoWidth,
      height: mobile ? undefined : videoHeight,
    },
  });
  video.srcObject = stream;

  return new Promise((resolve) => {
    video.onloadedmetadata = () => {
      resolve(video);
    };
  });
}

async function loadVideo() {
  const video = await setupCamera();
  video.play();
  return video;
}

//set up tracker
setTarget(255, 255, 255); // by default track white
tracking.ColorTracker.registerColor('match', function(r, g, b) {
  if (r <= rhi && r >= rlo &&
    g <= ghi && g >= glo &&
    b <= bhi && b >= blo) {
    return true;
  }
  return false;
});
// tracker = new tracking.ColorTracker(['match']);
// tracker.minDimension = 20;

var canvas = document.getElementById('output');
var context = canvas.getContext('2d');


var track = function() {
  var colors = new tracking.ColorTracker(['match']);
  colors.minDimension = guiState.segmentation.minBlobSize;
  colors.on('track', function(event) {
    if (event.data.length === 0) {} else {
      event.data.forEach(function(rect) {
        context.lineWidth = 6;
        context.strokeStyle = 'yellow';
        context.rect(rect.x, rect.y, rect.width, rect.height);
        context.stroke()
        var centerX = rect.x + rect.width / 2;
        var centerY = rect.y + rect.height / 2;


        x[0]=({
          type: 'float',
          value: parseFloat(centerX) || 0
        })

        y[0]=({
          type: 'float',
          value: parseFloat(centerY) || 0
        })
        if (guiState.segmentation.sendOSC && guiState.segmentation.maskMode==2)
        socket.emit('message', ['/wek/inputs', x, y]);
        // console.log(x+" "+y);
      });
    }
  });
  tracking.track('#output', colors);
}

const guiState = {
  estimate: 'segmentation',
  input: {
    mobileNetArchitecture: isMobile() ? '0.50' : '0.75',
    outputStride: 16
  },
  singlePoseDetection: {
    minPoseConfidence: 0.1,
    minPartConfidence: 0.5,
    segmentationThreshold: 0.5,
  },
  segmentation: {
    segmentationThreshold: 0.5,
    effect: 'mask',
    maskMode: 0,
    bokehBlurAmount: 3,
    track: true,
    minBlobSize: 100,
    sendOSC:false,
  },
  partMap: {
    colorScale: 0
  },
  net: null,
};


/**
 * Sets up a frames per second panel on the top-left of the window
 */
function setupFPS() {
  stats.showPanel(0);
  document.body.appendChild(stats.dom);
}

/**
 * Sets up dat.gui controller on the top-right of the window
 */
function setupGui(cameras, net) {
  guiState.net = net;

  if (cameras.length > 0) {
    guiState.camera = cameras[0].deviceId;
  }

  const gui = new dat.GUI({
    width: 300
  });

  // The single-pose algorithm is faster and simpler but requires only one
  // person to be in the frame or results will be innaccurate. Multi-pose works
  // for more than 1 person
  const estimateController =
    gui.add(guiState, 'estimate', ['segmentation', 'partmap']);

  // The input parameters have the most effect on accuracy and speed of the
  // network
  let input = gui.addFolder('Input');
  // Architecture: there are a few PoseNet models varying in size and
  // accuracy. 1.00 is the largest, but will be the slowest. 0.50 is the
  // fastest, but least accurate.
  const architectureController = input.add(
    guiState.input, 'mobileNetArchitecture', ['1.00', '0.75', '0.50', '0.25']);
  // Output stride:  Internally, this parameter affects the height and width of
  // the layers in the neural network. The lower the value of the output stride
  // the higher the accuracy but slower the speed, the higher the value the
  // faster the speed but lower the accuracy.
  input.add(guiState.input, 'outputStride', [8, 16, 32]);

  input.open();

  // Pose confidence: the overall confidence in the estimation of a person's
  // pose (i.e. a person detected in a frame)
  // Min part confidence: the confidence that a particular estimated keypoint
  // position is accurate (i.e. the elbow's position)
  let single = gui.addFolder('Single Pose Detection');
  single.add(guiState.singlePoseDetection, 'minPoseConfidence', 0.0, 1.0);
  single.add(guiState.singlePoseDetection, 'minPartConfidence', 0.0, 1.0);
  single.close();

  let segmentation = gui.addFolder('Segmentation');
  segmentation.add(guiState.segmentation, 'segmentationThreshold', 0.0, 1.0);
  segmentation.add(guiState.segmentation, 'effect', ['mask', 'bokeh']);
  segmentation.add(guiState.segmentation, 'maskMode', [0, 1, 2]);
  segmentation.add(guiState.segmentation, 'track');
  segmentation.add(guiState.segmentation, 'sendOSC');
  segmentation.add(guiState.segmentation, 'minBlobSize', 0, 640);
  segmentation
    .add(
      guiState.segmentation,
      'bokehBlurAmount',
    )
    .min(1)
    .max(20)
    .step(1);
  segmentation.open();

  let partMap = gui.addFolder('Part Map');
  partMap.add(guiState.partMap, 'colorScale', Object.keys(partColorScales));

  architectureController.onChange(function(architecture) {
    guiState.changeToArchitecture = architecture;
  });

  estimateController.onChange(function(estimationType) {
    if (estimationType === 'single-pose') {
      single.open();
      segmentation.close();
      partMap.close();
    } else if (estimationType === 'segmentation') {
      single.close();
      segmentation.open();
      partMap.close();
    } else {
      single.close();
      segmentation.open();
      partMap.open();
    }
  });
}




/**
 * Feeds an image to posenet to estimate poses - this is where the magic
 * happens. This function loops with a requestAnimationFrame method.
 */
function segmentBodyInRealTime(video, net) {
  const canvas = document.getElementById('output');
  // since images are being fed from a webcam
  const flipHorizontal = true;

  async function bodySegmentationFrame() {
    if (guiState.changeToArchitecture) {
      // Important to purge variables and free up GPU memory
      guiState.net.dispose();

      // Load the PoseNet model weights for either the 0.50, 0.75, 1.00, or 1.01
      // version
      guiState.net = await personSegmentation.load(+guiState.changeToArchitecture);

      guiState.changeToArchitecture = null;
    }

    // Begin monitoring code for frames per second
    // stats.begin();

    // Scale an image down to a certain factor. Too large of an image will slow
    // down the GPU
    const outputStride = +guiState.input.outputStride;

    switch (guiState.estimate) {
      case 'segmentation':
        const bodySegmentation = await guiState.net.estimatePersonSegmentation(
          video, flipHorizontal, outputStride,
          guiState.segmentation.segmentationThreshold);

        switch (guiState.segmentation.effect) {
          case 'mask':
            personSegmentation.drawBodyMaskOnCanvas(video, bodySegmentation, canvas, guiState.segmentation.maskMode);

            break;
          case 'bokeh':
            personSegmentation.drawBokehEffectOnCanvas(
              canvas, video, bodySegmentation, +guiState.segmentation.bokehBlurAmount);
            break;
        }
        break;
      case 'partmap':
        const partSegmentation = await guiState.net.estimatePartSegmentation(
          video, flipHorizontal, outputStride,
          guiState.segmentation.segmentationThreshold);

        personSegmentation.drawBodySegmentsOnCanvas(
          canvas, video, partSegmentation,
          partColorScales[guiState.partMap.colorScale]);

        break;
      default:
        break;
    }

    // End monitoring code for frames per second
    stats.end();

    if (guiState.segmentation.track == true && guiState.segmentation.maskMode == 2)
      track();

    requestAnimationFrame(bodySegmentationFrame);
  }

  bodySegmentationFrame();
}

/**
 * Kicks off the demo by loading the posenet model, finding and loading
 * available camera devices, and setting off the detectPoseInRealTime function.
 */
async function bindPage() {
  // Load the personSegmentation model weights with architecture 0.75
  const net = await personSegmentation.load(+guiState.input.mobileNetArchitecture);

  document.getElementById('loading').style.display = 'none';
  document.getElementById('main').style.display = 'block';

  let video;

  try {
    video = await loadVideo();
  } catch (e) {
    let info = document.getElementById('info');
    info.textContent = 'this browser does not support video capture,' +
      'or this device does not have a camera';
    info.style.display = 'block';
    throw e;
  }

  // setupFPS();
  setupGui([], net);

  segmentBodyInRealTime(video, net);
}

navigator.getUserMedia = navigator.getUserMedia ||
  navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
// kick off the demo
bindPage();
