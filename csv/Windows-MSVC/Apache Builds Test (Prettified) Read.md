
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 851.43 | 0.380935 | 7257.15ms | 124597 | 2560 | 7.23537e+08 | 139559 | 0.507359 | 2.90716 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 848.736 | 0.542542 | 7249.46ms | 124597 | 1280 | 7.38494e+08 | 140002 | 0.858347 | 2.91615 | 1(Tie) | true |
