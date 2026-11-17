
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3133.63 | 0.0799681 | 640.496ms | 18245 | 30 | 591.49 | 5552.6 | 0.0743842 | 0.786477 | 1(Win) | true |
| Jsonifier | 2687.27 | 0.0940643 | 736.324ms | 18245 | 30 | 1112.85 | 6474.9 | 0.0406864 | 0.917488 | 2(Loss) | true |
| simdjson (reflection) | 2562.69 | 0.208413 | 767.041ms | 18245 | 2560 | 512606 | 6789.65 | 0.0304324 | 0.962384 | 3(Loss) | true |
| simdjson (ondemand) | 2089.8 | 0.246367 | 922.274ms | 18245 | 1280 | 538583 | 8326.04 | 0.220964 | 1.18103 | 4(Loss) | true |
| Glaze | 2049.09 | 0.0521726 | 904.299ms | 18245 | 40 | 785.076 | 8491.48 | 0.081094 | 1.2043 | 5(Loss) | true |
