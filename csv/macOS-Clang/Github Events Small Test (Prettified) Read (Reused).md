
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1471.51 | 0.111093 | 159.417ms | 2158 | 4890 | 11804.6 | 1398.58 | 0.284922 | 1(Win) | true |
| simdjson (ondemand) | 1225.64 | 0.202121 | 188.895ms | 2158 | 40 | 460.746 | 1679.15 | 0.17142 | 2(Loss) | true |
