
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 890.907 | 1.09981 | 9143.02ms | 2251027 | 40 | 2.80927e+10 | 2.40962e+06 | 0.0157676 | 3.41117 | 1(Win) | true |
| Jsonifier (two-stage) | 831.155 | 0.484587 | 9668.02ms | 2251027 | 160 | 2.50646e+10 | 2.58285e+06 | 0.451305 | 3.65634 | 2(Loss) | true |
| simdjson (ondemand) | 485.605 | 0.32465 | 7412.61ms | 2251027 | 30 | 6.1794e+09 | 4.42076e+06 | 0.609356 | 6.25864 | 3(Loss) | true |
| Glaze | 448.047 | 0.466497 | 7964.08ms | 2251027 | 80 | 3.9967e+10 | 4.79134e+06 | 0.147731 | 6.78316 | 4(Loss) | true |
