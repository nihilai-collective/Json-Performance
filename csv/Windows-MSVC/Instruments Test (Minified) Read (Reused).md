
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1187.45 | 0.0724425 | 8998.89ms | 108313 | 1280 | 5.08308e+06 | 86989.1 | 0.0934049 | 2.55886 | 1(Win) | true |
| simdjson (ondemand) | 999.608 | 0.0581956 | 5405.86ms | 108313 | 2560 | 9.25812e+06 | 103336 | 0.127402 | 3.03985 | 2(Loss) | true |
