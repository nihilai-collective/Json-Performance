
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2433 | 0.454142 | 10122.6ms | 7351818 | 40 | 6.85092e+09 | 2.88173e+06 | 0.563031 | 1.01759 | 1(Win) | true |
| Jsonifier | 2327.02 | 0.595153 | 5046.34ms | 7351818 | 30 | 9.64643e+09 | 3.01297e+06 | 0.380025 | 1.06393 | 2(Loss) | true |
| simdjson (ondemand) | 838.262 | 0.262997 | 6080.81ms | 7351818 | 40 | 1.93549e+10 | 8.36402e+06 | 0.277929 | 2.9535 | 3(Loss) | true |
| Glaze | 733.652 | 0.659307 | 6961.99ms | 7351818 | 30 | 1.19099e+11 | 9.55663e+06 | 0.066576 | 3.37464 | 4(Loss) | true |
