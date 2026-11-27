
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 783.384 | 0.337922 | 707.12ms | 4926 | 40 | 16426 | 5996.8 | 0.177557 | 1(Win) | true |
| simdjson (ondemand) | 356.493 | 0.167187 | 1456.8ms | 4926 | 1280 | 621298 | 13177.8 | 0.0227604 | 2(Loss) | true |
