
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2422.85 | 0.0885518 | 217.897ms | 4857 | 160 | 458.564 | 1911.8 | 0.556881 | 1.0069 | 1(Win) | true |
| Jsonifier (two-stage) | 2064.62 | 0.106838 | 255.358ms | 4857 | 80 | 459.62 | 2243.51 | 0.116583 | 1.18416 | 2(Loss) | true |
| Glaze | 1942.69 | 0.244694 | 260.658ms | 4857 | 4890 | 166450 | 2384.32 | 0.355302 | 1.2585 | 3(Loss) | true |
| simdjson (ondemand) | 853.964 | 0.637307 | 584.813ms | 4857 | 320 | 382389 | 5424.11 | 0.184009 | 2.8836 | 4(Loss) | true |
