
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 742.772 | 0.281993 | 8150.16ms | 1834197 | 160 | 7.05632e+09 | 2.355e+06 | 0.0233226 | 4.09163 | 1(Win) | true |
| Jsonifier (two-stage) | 642.353 | 0.215579 | 9273.38ms | 1834197 | 160 | 5.51413e+09 | 2.72316e+06 | 0.49794 | 4.73124 | 2(Loss) | true |
| simdjson (ondemand) | 379.171 | 0.194227 | 7332.36ms | 1834197 | 80 | 6.42292e+09 | 4.61329e+06 | 0.328509 | 8.01562 | 3(Loss) | true |
| Glaze | 336.781 | 0.429921 | 8238.81ms | 1834197 | 40 | 1.9945e+10 | 5.19396e+06 | 0.409176 | 9.02462 | 4(Loss) | true |
