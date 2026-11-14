
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4840.8 | 0.460343 | 5158.66ms | 466906 | 80 | 1.43442e+07 | 91984 | 0.100785 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4832.9 | 0.201754 | 5043.48ms | 466906 | 30 | 1.0366e+06 | 92134.4 | 0.184894 | 1(Tie) | true |
| simdjson (reflection) | 3919.44 | 0.227488 | 6030.07ms | 466906 | 640 | 4.27472e+07 | 113607 | 0.100597 | 3(Loss) | true |
| simdjson (ondemand) | 3697.03 | 0.102286 | 6427.23ms | 466906 | 2560 | 3.88532e+07 | 120442 | 2.12337 | 4(Loss) | true |
| Glaze | 2308.72 | 0.154237 | 5215.75ms | 466906 | 1280 | 1.13267e+08 | 192867 | 0.407011 | 5(Loss) | true |
