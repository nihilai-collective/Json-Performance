
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2158.28 | 0.107846 | 5342.61ms | 7351818 | 30 | 3.68219e+08 | 3.24853e+06 | 0.418025 | 1.40812 | 1(Win) | true |
| Jsonifier | 2115.82 | 0.103907 | 5423.78ms | 7351818 | 30 | 3.55666e+08 | 3.31372e+06 | 0.482645 | 1.43636 | 2(Loss) | true |
| simdjson (ondemand) | 1220.85 | 0.0792852 | 9073.64ms | 7351818 | 40 | 8.29301e+08 | 5.74294e+06 | 0.0141643 | 2.48951 | 3(Loss) | true |
| Glaze | 1091.48 | 0.324055 | 10103.1ms | 7351818 | 80 | 3.46648e+10 | 6.42362e+06 | 0.262091 | 2.78463 | 4(Loss) | true |
