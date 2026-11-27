
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 23361.2 | 0.120378 | 7694.74ms | 1834197 | 640 | 5.19969e+06 | 74877.4 | 0.0256604 | 0.105944 | 1(Win) | true |
| simdjson (stage-1) | 18284.9 | 0.0513743 | 9649.77ms | 1834197 | 4890 | 1.18116e+07 | 95665.1 | 0.143588 | 0.135362 | 2(Loss) | true |
