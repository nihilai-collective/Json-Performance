
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2394.78 | 0.226902 | 10210ms | 7351818 | 160 | 7.06082e+09 | 2.92772e+06 | 0.501935 | 1.03382 | 1(Win) | true |
| Jsonifier (two-stage) | 2380.04 | 0.183918 | 10042.4ms | 7351818 | 40 | 1.17417e+09 | 2.94585e+06 | 0.213516 | 1.04024 | 2(Loss) | true |
| simdjson (ondemand) | 892.064 | 2.23276 | 5583.78ms | 7351818 | 30 | 9.23852e+11 | 7.85957e+06 | 2.16468 | 2.77539 | 3(Loss) | true |
| Glaze | 730.026 | 0.845624 | 7261.91ms | 7351818 | 40 | 2.63832e+11 | 9.60409e+06 | 1.4828 | 3.39135 | 4(Loss) | true |
