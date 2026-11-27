
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 271.334 | 0.0682297 | 1774.6ms | 4604 | 30 | 3657.03 | 16181.9 | 0.0255494 | 1(Win) | true |
| simdjson (ondemand) | 168.897 | 0.0755995 | 2790.39ms | 4604 | 4890 | 1.88875e+06 | 25996.4 | 0.0673978 | 2(Loss) | true |
