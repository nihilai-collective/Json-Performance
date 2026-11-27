
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1251.55 | 0.108984 | 8402.54ms | 108313 | 1280 | 1.03562e+07 | 82533.8 | 0.244618 | 1(Win) | true |
| simdjson (ondemand) | 1162.31 | 0.099425 | 9089.48ms | 108313 | 640 | 4.99677e+06 | 88870.8 | 0.115807 | 2(Loss) | true |
