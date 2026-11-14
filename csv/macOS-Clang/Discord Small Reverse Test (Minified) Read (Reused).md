
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 675.175 | 0.0593233 | 746.096ms | 4857 | 80 | 1325.08 | 6860.44 | 0.0136672 | 1(Win) | true |
| simdjson (ondemand) | 135.692 | 0.325662 | 3589.33ms | 4857 | 1280 | 1.58188e+07 | 34136.2 | 0.134406 | 2(Loss) | true |
