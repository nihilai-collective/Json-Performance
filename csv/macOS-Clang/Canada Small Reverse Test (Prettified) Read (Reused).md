
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1073.08 | 0.0656372 | 1152.62ms | 11579 | 40 | 1824.91 | 10290.6 | 0.138181 | 1(Win) | true |
| simdjson (ondemand) | 1052.2 | 0.0741618 | 1175ms | 11579 | 40 | 2423.06 | 10494.8 | 0.0623732 | 2(Loss) | true |
