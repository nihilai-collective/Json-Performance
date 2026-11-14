
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1170.55 | 0.121168 | 4970.25ms | 53331 | 4890 | 1.3554e+07 | 43450.1 | 0.0849481 | 2.59498 | 1(Win) | true |
| simdjson (ondemand) | 934.769 | 0.0437097 | 6075.94ms | 53331 | 4890 | 2.76577e+06 | 54409.6 | 0.122956 | 3.24998 | 2(Loss) | true |
