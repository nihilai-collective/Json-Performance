
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2264.75 | 0.0501955 | 6909.46ms | 124597 | 4890 | 3.39168e+06 | 52467.2 | 0.0624136 | 1(Win) | true |
| Jsonifier (two-stage) | 1858.06 | 0.0308399 | 8430.31ms | 124597 | 40 | 15559 | 63951.1 | 0.103741 | 2(Loss) | true |
| Glaze | 1728.7 | 0.0810828 | 8546.28ms | 124597 | 2560 | 7.95191e+06 | 68736.4 | 2.05972 | 3(Loss) | true |
| simdjson (ondemand) | 1366.46 | 0.137549 | 5426.1ms | 124597 | 320 | 4.57814e+06 | 86958.4 | 0.102734 | 4(Loss) | true |
