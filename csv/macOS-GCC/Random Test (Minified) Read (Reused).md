
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1634.16 | 0.92065 | 10026.8ms | 461466 | 40 | 2.45889e+08 | 269306 | 2.38532 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.37 | 0.162548 | 5595.17ms | 461466 | 40 | 1.09478e+07 | 321850 | 0.0774917 | 2(Loss) | true |
| Glaze | 1035.61 | 0.182531 | 7613.82ms | 461466 | 80 | 4.81332e+07 | 424954 | 0.0874271 | 3(Loss) | true |
| simdjson (reflection) | 986.653 | 0.113066 | 6961.2ms | 461466 | 640 | 1.62776e+08 | 446042 | 0.231905 | 4(Loss) | true |
| simdjson (ondemand) | 878.355 | 0.117989 | 7642.52ms | 461466 | 320 | 1.11833e+08 | 501037 | 0.010537 | 5(Loss) | true |
