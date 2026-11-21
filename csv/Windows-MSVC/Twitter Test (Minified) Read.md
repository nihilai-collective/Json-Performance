
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1312.38 | 1.9509 | 8697.85ms | 466906 | 80 | 3.50511e+09 | 339290 | 1.04341 | 1.88622 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1141.48 | 1.34242 | 5168.1ms | 466906 | 80 | 2.19376e+09 | 390088 | 4.10769 | 2.16873 | -(Loss) | false |
| Glaze STATISTICAL TIE | 1078.39 | 1.01838 | 5283.7ms | 466906 | 320 | 5.65818e+09 | 412909 | 0.322725 | 2.2956 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1056.38 | 0.483554 | 5599.87ms | 466906 | 320 | 1.3294e+09 | 421511 | 2.77651 | 2.34339 | -(Tie) | false |
