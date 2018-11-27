// @tensorflow/tfjs-models Copyright 2018 Google
! function(e, t) {
  "object" == typeof exports && "undefined" != typeof module ? t(exports, require("@tensorflow/tfjs")) : "function" == typeof define && define.amd ? define(["exports", "@tensorflow/tfjs"], t) : t(e.personSegmentation = {}, e.tf)
}(this, function(e, t) {
  "use strict";
  var r = [
      ["conv2d", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1]
    ],
    n = [8, 16, 32];

  function o(e) {
    t.util.assert("number" == typeof e, "outputStride is not a number"), t.util.assert(n.indexOf(e) >= 0, "outputStride of " + e + " is invalid. It must be either 8, 16, or 32")
  }
  var a = {
    100: [
      ["conv2d", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1]
    ],
    75: [
      ["conv2d", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 2],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1],
      ["separableConv", 1]
    ],
    50: r,
    25: r
  };
  var i = function() {
      function e(e, r) {
        this.PREPROCESS_DIVISOR = t.scalar(127.5), this.ONE = t.scalar(1), this.modelWeights = e, this.convolutionDefinitions = r
      }
      return e.prototype.predict = function(e, r) {
        var n = this,
          o = t.div(e.toFloat(), this.PREPROCESS_DIVISOR),
          a = t.sub(o, this.ONE);
        return function(e, t) {
          var r = 1,
            n = 1;
          return e.map(function(e, o) {
            var a, i, s = e[0],
              u = e[1];
            return r === t ? (a = 1, i = n, n *= u) : (a = u, i = 1, r *= u), {
              blockId: o,
              convType: s,
              stride: a,
              rate: i,
              outputStride: r
            }
          })
        }(this.convolutionDefinitions, r).reduce(function(e, t) {
          var r = t.blockId,
            o = t.stride,
            a = t.convType,
            i = t.rate;
          if ("conv2d" === a) return n.conv(e, o, r);
          if ("separableConv" === a) return n.separableConv(e, o, r, i);
          throw Error("Unknown conv type of " + a)
        }, a)
      }, e.prototype.convToOutput = function(e, t) {
        return e.conv2d(this.weights(t), 1, "same").add(this.convBias(t, !1))
      }, e.prototype.conv = function(e, t, r) {
        var n = this.weights("Conv2d_" + String(r));
        return e.conv2d(n, t, "same").add(this.convBias("Conv2d_" + String(r))).clipByValue(0, 6)
      }, e.prototype.separableConv = function(e, t, r, n) {
        void 0 === n && (n = 1);
        var o = "Conv2d_" + String(r) + "_depthwise",
          a = "Conv2d_" + String(r) + "_pointwise";
        return e.depthwiseConv2D(this.depthwiseWeights(o), t, "same", "NHWC", n).add(this.depthwiseBias(o)).clipByValue(0, 6).conv2d(this.weights(a), [1, 1], "same").add(this.convBias(a)).clipByValue(0, 6)
      }, e.prototype.weights = function(e) {
        return this.modelWeights.weights(e)
      }, e.prototype.convBias = function(e, t) {
        return void 0 === t && (t = !0), this.modelWeights.convBias(e, t)
      }, e.prototype.depthwiseBias = function(e) {
        return this.modelWeights.depthwiseBias(e)
      }, e.prototype.depthwiseWeights = function(e) {
        return this.modelWeights.depthwiseWeights(e)
      }, e.prototype.dispose = function() {
        this.modelWeights.dispose()
      }, e
    }(),
    s = "https://storage.googleapis.com/tfjs-models/savedmodel/",
    u = {
      1: {
        url: s + "posenet_mobilenet_100_partmap/",
        architecture: a[100]
      },
      .75: {
        url: s + "posenet_mobilenet_075_partmap/",
        architecture: a[75]
      },
      .5: {
        url: s + "posenet_mobilenet_050_partmap/",
        architecture: a[50]
      },
      .25: {
        url: s + "posenet_mobilenet_025_partmap/",
        architecture: a[25]
      }
    };

  function l(e, r) {
    return t.tidy(function() {
      return e.greater(t.scalar(r)).toInt()
    })
  }

  function p(e, r) {
    var n = r.shape,
      o = n[0],
      a = n[1],
      i = n[2];
    return t.tidy(function() {
      var n, s, u = function(e) {
          var r = e.shape[2],
            n = e.argMax(2).reshape([-1]);
          return t.oneHot(n, r)
        }(r),
        l = t.range(0, i, 1, "int32").expandDims(1),
        p = u.matMul(l).toInt().reshape([o, a]).add(t.scalar(1, "int32"));
      return (n = p, s = e, n.mul(s)).sub(t.scalar(1, "int32"))
    })
  }
  var d = {};

  function c(e) {
    var t = e.getContext("2d");
    t.scale(-1, 1), t.translate(-e.width, 0)
  }

  function f(e, t, r) {
    e.globalCompositeOperation = r, e.drawImage(t, 0, 0)
  }

  function h(e) {
    return d[e] || (d[e] = document.createElement("canvas")), d[e]
  }

  function v(e, t, r) {
    var n = e.height,
      o = e.width,
      a = r.getContext("2d");
    r.width = o, r.height = n, a.clearRect(0, 0, o, n), a.save(), /^((?!chrome|android).)*safari/i.test(navigator.userAgent) ? function(e, t, r) {
      for (var n = e.getContext("2d"), o = 0, a = 1 / (2 * Math.PI * 5 * 5), i = r < 3 ? 1 : 2, s = -r; s <= r; s += i)
        for (var u = -r; u <= r; u += i) o += a * Math.exp(-(u * u + s * s) / 50);
      for (s = -r; s <= r; s += i)
        for (u = -r; u <= r; u += i) n.globalAlpha = a * Math.exp(-(u * u + s * s) / 50) / o * r, n.drawImage(t, u, s);
      n.globalAlpha = 1
    }(r, e, t) : (a.filter = "blur(" + t + "px)", a.drawImage(e, 0, 0, o, n)), a.restore()
  }

  function b(e, t, r, n) {
    n.width = t, n.height = r, n.getContext("2d").putImageData(e, 0, 0)
  }
  //m is mode, 0 for normal, 1 for see through total black mask, 2, for white mask
  //t, o, a, !0, .7, m
  function g(e, t, r, n, o, m) {
    void 0 === o && (o = .7);
    for (var a = new Uint8ClampedArray(r * t * 4), i = Math.round(255 * o), s = 0; s < t * r; ++s) {
      var u = (n ? 1 - e[s] : e[s]) * i,
        l = 4 * s;
        if (m==0)
          a[l + 0] = 0, a[l + 1] = 0, a[l + 2] = 0, a[l + 3] = Math.round(u)
        else if (m==1){
          u = (u > 0 ? 255 : 0)
          a[l + 0] = 0, a[l + 1] = 0, a[l + 2] = 0, a[l + 3] = Math.round(u)
        } else if (m==2){
          u = (u > 0 ? 255 : 0)
          if (u == 0) {
            a[l + 0] = 255, a[l + 1] = 255, a[l + 2] = 255, a[l + 3] = 255
          } else
            a[l + 0] = 0, a[l + 1] = 0, a[l + 2] = 0, a[l + 3] = 255;
        } else
          a[l + 0] = 0, a[l + 1] = 0, a[l + 2] = 0, a[l + 3] = Math.round(u)
    }
    return new ImageData(a, r, t)
  }

  function m(e, t, r, n) {
    return new(r || (r = Promise))(function(o, a) {
      function i(e) {
        try {
          u(n.next(e))
        } catch (e) {
          a(e)
        }
      }

      function s(e) {
        try {
          u(n.throw(e))
        } catch (e) {
          a(e)
        }
      }

      function u(e) {
        e.done ? o(e.value) : new r(function(t) {
          t(e.value)
        }).then(i, s)
      }
      u((n = n.apply(e, t || [])).next())
    })
  }

  function _(e, t) {
    var r, n, o, a, i = {
      label: 0,
      sent: function() {
        if (1 & o[0]) throw o[1];
        return o[1]
      },
      trys: [],
      ops: []
    };
    return a = {
      next: s(0),
      throw: s(1),
      return: s(2)
    }, "function" == typeof Symbol && (a[Symbol.iterator] = function() {
      return this
    }), a;

    function s(a) {
      return function(s) {
        return function(a) {
          if (r) throw new TypeError("Generator is already executing.");
          for (; i;) try {
            if (r = 1, n && (o = 2 & a[0] ? n.return : a[0] ? n.throw || ((o = n.return) && o.call(n), 0) : n.next) && !(o = o.call(n, a[1])).done) return o;
            switch (n = 0, o && (a = [2 & a[0], o.value]), a[0]) {
              case 0:
              case 1:
                o = a;
                break;
              case 4:
                return i.label++, {
                  value: a[1],
                  done: !1
                };
              case 5:
                i.label++, n = a[1], a = [0];
                continue;
              case 7:
                a = i.ops.pop(), i.trys.pop();
                continue;
              default:
                if (!(o = (o = i.trys).length > 0 && o[o.length - 1]) && (6 === a[0] || 2 === a[0])) {
                  i = 0;
                  continue
                }
                if (3 === a[0] && (!o || a[1] > o[0] && a[1] < o[3])) {
                  i.label = a[1];
                  break
                }
                if (6 === a[0] && i.label < o[1]) {
                  i.label = o[1], o = a;
                  break
                }
                if (o && i.label < o[2]) {
                  i.label = o[2], i.ops.push(a);
                  break
                }
                o[2] && i.ops.pop(), i.trys.pop();
                continue
            }
            a = t.call(e, i)
          } catch (e) {
            a = [6, e], n = 0
          } finally {
            r = o = 0
          }
          if (5 & a[0]) throw a[1];
          return {
            value: a[0] ? a[1] : void 0,
            done: !0
          }
        }([a, s])
      }
    }
  }
  var w = function() {
    function e(e) {
      this.frozenModel = e
    }
    return e.prototype.weights = function(e) {
      return this.getVariable("MobilenetV1/" + e + "/weights")
    }, e.prototype.convBias = function(e, t) {
      return void 0 === t && (t = !0), this.getVariable("MobilenetV1/" + e + "/Conv2D_bias")
    }, e.prototype.depthwiseBias = function(e) {
      return this.getVariable("MobilenetV1/" + e + "/depthwise_bias")
    }, e.prototype.depthwiseWeights = function(e) {
      return this.getVariable("MobilenetV1/" + e + "/depthwise_weights")
    }, e.prototype.getVariable = function(e) {
      return this.frozenModel.weights["" + e][0]
    }, e.prototype.dispose = function() {
      this.frozenModel.dispose()
    }, e
  }();

  function C(e) {
    return e instanceof t.Tensor ? [e.shape[0], e.shape[1]] : [e.height, e.width]
  }

  function y(e, r, n) {
    var o = r[0],
      a = r[1];
    void 0 === n && (n = !1);
    var i, s, u, l, p, d, c = C(e),
      f = c[0],
      h = c[1] / f;
    if (h > a / o) {
      i = a;
      var v = o - (s = Math.ceil(i / h));
      u = 0, l = 0, p = Math.floor(v / 2), d = o - (s + p)
    } else {
      s = o;
      var b = a - (i = Math.ceil(o / h));
      u = Math.floor(b / 2), l = a - (i + u), p = 0, d = 0
    }
    return {
      resizedAndPadded: t.tidy(function() {
        var r, o = function(e) {
          return e instanceof t.Tensor ? e : t.fromPixels(e)
        }(e);
        return r = n ? o.reverse(1).resizeBilinear([s, i]) : o.resizeBilinear([s, i]), t.pad3d(r, [
          [p, d],
          [u, l],
          [0, 0]
        ])
      }),
      paddedBy: [
        [p, d],
        [u, l]
      ]
    }
  }

  function S(e, r, n, o) {
    var a = r[0],
      i = r[1],
      s = n[0],
      u = n[1],
      l = o[0],
      p = l[0],
      d = l[1],
      c = o[1],
      f = c[0],
      h = c[1];
    return t.tidy(function() {
      return function(e, r, n) {
        var o = r[0],
          a = r[1],
          i = n[0],
          s = i[0],
          u = i[1],
          l = n[1],
          p = l[0],
          d = l[1],
          c = e.shape,
          f = c[0],
          h = c[1],
          v = f - (s + u),
          b = h - (p + d);
        return t.tidy(function() {
          var r = t.slice3d(e, [s, p, 0], [v, b, e.shape[2]]),
            n = r.resizeBilinear([o, a], !0);
          return n
        })
      }(e.resizeBilinear([s, u], !0), [a, i], [
        [p, d],
        [f, h]
      ])
    })
  }
  var M = [353, 257],
    x = function() {
      function e(e) {
        this.mobileNet = e
      }
      return e.prototype.predictForSegmentation = function(e, r) {
        var n = this;
        return void 0 === r && (r = 16), o(r), t.tidy(function() {
          var t = n.mobileNet.predict(e, r);
          return n.mobileNet.convToOutput(t, "segment_2").sigmoid()
        })
      }, e.prototype.predictForPartMap = function(e, r) {
        var n = this;
        return void 0 === r && (r = 16), o(r), t.tidy(function() {
          var t = n.mobileNet.predict(e, r),
            o = n.mobileNet.convToOutput(t, "segment_2"),
            a = n.mobileNet.convToOutput(t, "part_heatmap_2");
          return {
            segmentScores: o.sigmoid(),
            partHeatmapScores: a.sigmoid()
          }
        })
      }, e.prototype.estimatePersonSegmentation = function(e, r, n, a) {
        return void 0 === r && (r = !1), void 0 === n && (n = 16), void 0 === a && (a = .5), m(this, void 0, void 0, function() {
          var i, s, u, p, d, c = this;
          return _(this, function(f) {
            switch (f.label) {
              case 0:
                return o(n), i = C(e), s = i[0], u = i[1], [4, (p = t.tidy(function() {
                  var t = y(e, M, r),
                    o = t.resizedAndPadded,
                    i = t.paddedBy,
                    p = c.predictForSegmentation(o, n),
                    d = o.shape,
                    f = d[0],
                    h = d[1],
                    v = l(S(p, [s, u], [f, h], i).squeeze(), a);
                  return r ? v.reverse(1) : v
                })).data()];
              case 1:
                return d = f.sent(), p.dispose(), [2, d]
            }
          })
        })
      }, e.prototype.estimatePartSegmentation = function(e, r, n, a) {
        return void 0 === r && (r = !1), void 0 === n && (n = 16), void 0 === a && (a = .5), m(this, void 0, void 0, function() {
          var i, s, u, d, c, f = this;
          return _(this, function(h) {
            switch (h.label) {
              case 0:
                return o(n), i = C(e), s = i[0], u = i[1], [4, (d = t.tidy(function() {
                  var t = y(e, M, r),
                    o = t.resizedAndPadded,
                    i = t.paddedBy,
                    d = f.predictForPartMap(o, n),
                    c = d.segmentScores,
                    h = d.partHeatmapScores,
                    v = o.shape,
                    b = v[0],
                    g = v[1],
                    m = S(c, [s, u], [b, g], i),
                    _ = S(h, [s, u], [b, g], i),
                    w = p(l(m.squeeze(), a), _);
                  return r ? w.reverse(1) : w
                })).data()];
              case 1:
                return c = h.sent(), d.dispose(), [2, c]
            }
          })
        })
      }, e.prototype.dispose = function() {
        this.mobileNet.dispose()
      }, e
    }();
  var k = {
    load: function(e) {
      return m(void 0, void 0, void 0, function() {
        var r, n, o, a;
        return _(this, function(s) {
          switch (s.label) {
            case 0:
              return r = u[e], n = r.url, [4, t.loadFrozenModel(n + "tensorflowjs_model.pb", n + "weights_manifest.json")];
            case 1:
              return o = s.sent(), a = new w(o), [2, new i(a, r.architecture)]
          }
        })
      })
    }
  };
  e.checkpoints = u, e.decodePartSegmentation = p, e.toMask = l, e.drawBodyMaskOnCanvas = function(e, t, r, m, n) {
    void 0 === n && (n = !0);
    var o = e.height,
      a = e.width,
      i = g(t, o, a, !0, .7, m),
      s = h("mask");
    b(i, a, o, s), r.width = a, r.height = o;
    var u = r.getContext("2d");
    u.save(), n && c(r), u.drawImage(e, 0, 0), f(u, s, "source-atop"), u.restore()
  }, e.drawBodySegmentsOnCanvas = function(e, t, r, n, o, a) {
    void 0 === o && (o = .7), void 0 === a && (a = !0);
    var i = t.height,
      s = t.width;
    e.width = s, e.height = i;
    var u = function(e, t, r, n, o) {
        for (var a = new Uint8ClampedArray(r * n * 4), i = 0; i < n * r; ++i) {
          var s = Math.round(e[i]),
            u = 4 * i;
          if (-1 === s) a[u + 0] = 0, a[u + 1] = 0, a[u + 2] = 0, a[u + 3] = Math.round(255 * o);
          else {
            var l = t[s];
            if (!l) throw new Error("No color could be found for part id " + s);
            a[u + 0] = l[0], a[u + 1] = l[1], a[u + 2] = l[2], a[u + 3] = Math.round(255 * o)
          }
        }
        return new ImageData(a, r, n)
      }(r, n, s, i, o),
      l = h("partImage");
    b(u, s, i, l);
    var p = e.getContext("2d");
    p.save(), a && c(e), p.drawImage(t, 0, 0), f(p, l, "source-over"), p.restore()
  }, e.drawBokehEffectOnCanvas = function(e, t, r, n, o) {
    void 0 === n && (n = 3), void 0 === o && (o = !0);
    var a = t.height,
      i = t.width,
      s = h("blur");
    v(t, n, s);
    var u = g(r, a, i, !1, 1),
      l = h("mask");
    b(u, i, a, l);
    var p = s.getContext("2d");
    p.save(), f(p, l, "destination-out"), p.restore();
    var d = e.getContext("2d");
    d.save(), o && c(e), d.drawImage(t, 0, 0), f(d, l, "destination-in"), f(d, s, "source-over"), d.restore()
  }, e.partChannels = ["left_face", "right_face", "right_upper_leg_front", "right_lower_leg_back", "right_upper_leg_back", "left_lower_leg_front", "left_upper_leg_front", "left_upper_leg_back", "left_lower_leg_back", "right_feet", "right_lower_leg_front", "left_feet", "torso_front", "torso_back", "right_upper_arm_front", "right_upper_arm_back", "right_lower_arm_back", "left_lower_arm_front", "left_upper_arm_front", "left_upper_arm_back", "left_lower_arm_back", "right_hand", "right_lower_arm_front", "left_hand"], e.load = function(e) {
    return void 0 === e && (e = .75), m(this, void 0, void 0, function() {
      var r, n;
      return _(this, function(o) {
        switch (o.label) {
          case 0:
            if (null == t) throw new Error("Cannot find TensorFlow.js. If you are using a <script> tag, please also include @tensorflow/tfjs on the page before using this model.");
            return r = Object.keys(u), t.util.assert("number" == typeof e, "got multiplier type of " + typeof e + " when it should be a number."), t.util.assert(r.indexOf(e.toString()) >= 0, "invalid multiplier value of " + e + ".  No checkpoint exists for that multiplier. Must be one of " + r.join(",") + "."), [4, k.load(e)];
          case 1:
            return n = o.sent(), [2, new x(n)]
        }
      })
    })
  }, e.PersonSegmentation = x, e.resizeAndPadTo = y, e.scaleAndCropToInputTensorShape = S, Object.defineProperty(e, "__esModule", {
    value: !0
  })
});
