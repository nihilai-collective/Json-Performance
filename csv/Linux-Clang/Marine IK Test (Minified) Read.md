
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23664.9 | 0.0410379 | 7421.47ms | 1834197 | 4890 | 4.49948e+06 | 73916.4 | 0.214935 | 0.104582 | 1(Win) | true |
| simdjson (stage-1) | 18535.1 | 0.0468413 | 9443.37ms | 1834197 | 4890 | 9.55585e+06 | 94373.8 | 0.0620657 | 0.133537 | 2(Loss) | true |
