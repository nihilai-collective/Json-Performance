
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1296.31 | 0.0590673 | 8308.53ms | 108313 | 640 | 1.41781e+06 | 79684.1 | 0.0556577 | 2.34395 | 1(Win) | true |
| simdjson (ondemand) | 1014.69 | 0.182608 | 5371.35ms | 108313 | 80 | 2.76456e+06 | 101800 | 0.199316 | 2.99475 | 2(Loss) | true |
