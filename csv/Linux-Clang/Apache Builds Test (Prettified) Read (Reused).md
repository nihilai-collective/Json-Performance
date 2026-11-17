
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2868.11 | 0.0344517 | 6179.98ms | 124597 | 4890 | 996213 | 41429.7 | 0.177035 | 1.7566 | 8.82096 | 1.49136 | 0.00483658 | 1.03467e-05 | 6.38131e-06 | 1(Win) | true |
| Jsonifier | 2504.81 | 0.0701003 | 6804.71ms | 124597 | 640 | 707762 | 47438.8 | 0.00998755 | 2.00614 | 9.71164 | 1.87017 | 0.00791567 | 5.09141e-06 | 1.85598e-06 | 2(Loss) | true |
| Glaze | 2227.21 | 0.0603504 | 7476.28ms | 124597 | 640 | 663489 | 53351.5 | 0.04909 | 2.26684 | 11.0249 | 2.11922 | 0.0103865 | 1.60768e-05 | 9.49311e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2131.9 | 0.0293497 | 7584.51ms | 124597 | 4890 | 1.30857e+06 | 55736.6 | 0.0914502 | 2.36014 | 10.112 | 1.73242 | 0.00571676 | 1.38902e-05 | 3.98339e-06 | 4(Loss) | true |
