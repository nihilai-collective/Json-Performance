
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1222.51 | 0.150387 | 1973.61ms | 25388 | 4890 | 4.33797e+06 | 19805.1 | 0.701775 | 1(Win) | true |
| simdjson (ondemand) | 1082.96 | 0.122616 | 2292.51ms | 25388 | 4890 | 3.67481e+06 | 22357.2 | 0.234627 | 2(Loss) | true |
