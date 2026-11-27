
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4422.36 | 0.454955 | 5029.51ms | 1834197 | 160 | 5.18132e+08 | 395541 | 0.105346 | 0.687089 | 1(Win) | true |
| simdjson (ondemand) | 4117.05 | 0.305777 | 5480.96ms | 1834197 | 80 | 1.35026e+08 | 424874 | 0.343331 | 0.738118 | 2(Loss) | true |
