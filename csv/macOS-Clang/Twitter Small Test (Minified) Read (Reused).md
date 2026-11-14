
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1772.61 | 0.141091 | 171.336ms | 2821 | 160 | 733.665 | 1517.71 | 0.069231 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1197.55 | 0.356108 | 224.041ms | 2821 | 1280 | 81919.8 | 2246.51 | 5.23319 | -(Loss) | false |
