
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1447.5 | 0.550132 | 7772.94ms | 7351818 | 30 | 2.13013e+10 | 4.84368e+06 | 0.339904 | 2.09964 | 1(Win) | true |
| simdjson (ondemand) | 1422.68 | 0.514252 | 7870.2ms | 7351818 | 80 | 5.13827e+10 | 4.92819e+06 | 0.383374 | 2.13629 | 2(Loss) | true |
