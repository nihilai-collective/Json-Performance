
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1914.79 | 0.190528 | 291.64ms | 4857 | 640 | 13595.4 | 2419.06 | 0.0645494 | 1.57515 | 1(Win) | true |
| Glaze | 1785.72 | 0.162795 | 302.741ms | 4857 | 1280 | 22824.4 | 2593.91 | 0.0783699 | 1.68953 | 2(Loss) | true |
| Jsonifier (two-stage) | 1308.8 | 0.0869683 | 410.491ms | 4857 | 4890 | 46325.7 | 3539.12 | 0.0204273 | 2.30881 | 3(Loss) | true |
| simdjson (ondemand) | 1063.91 | 0.147002 | 476.122ms | 4857 | 80 | 3276.9 | 4353.75 | 0.201381 | 2.84095 | 4(Loss) | true |
