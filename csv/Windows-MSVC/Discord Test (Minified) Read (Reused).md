
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1150.81 | 0.146981 | 5249.31ms | 56369 | 1280 | 6.03401e+06 | 46712.9 | 0.0979342 | 2.15021 | 1(Win) | true |
| simdjson (ondemand) | 969.577 | 0.0692623 | 6035.41ms | 56369 | 4890 | 7.2114e+06 | 55444.5 | 0.0341569 | 2.55221 | 2(Loss) | true |
