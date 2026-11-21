
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1144.86 | 0.131465 | 469.334ms | 4604 | 4890 | 124307 | 3835.16 | 0.0850006 | 2.1473 | 1(Win) | true |
| Jsonifier (two-stage) | 1039.65 | 0.0515137 | 502.574ms | 4604 | 160 | 757.292 | 4223.27 | 0.0962485 | 2.36651 | 2(Loss) | true |
| Glaze | 783.399 | 0.148571 | 647.795ms | 4604 | 30 | 2080.15 | 5604.7 | 0.197657 | 3.14513 | 3(Loss) | true |
| simdjson (ondemand) | 609.677 | 0.158861 | 803.77ms | 4604 | 1280 | 167538 | 7201.71 | 0.0216698 | 4.04547 | 4(Loss) | true |
