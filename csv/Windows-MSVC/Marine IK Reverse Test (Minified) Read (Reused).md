
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 278.499 | 0.476201 | 10063.5ms | 1834197 | 40 | 3.57836e+10 | 6.2809e+06 | 0.894477 | 10.9128 | 1(Win) | true |
| simdjson (ondemand) | 210.714 | 0.677775 | 6073.96ms | 1834197 | 30 | 9.49724e+10 | 8.30143e+06 | 0.457507 | 14.424 | 2(Loss) | true |
