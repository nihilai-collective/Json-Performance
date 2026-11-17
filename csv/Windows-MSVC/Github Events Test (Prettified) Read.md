
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1023 | 0.141065 | 6111.13ms | 65103 | 80 | 586378 | 60691.2 | 0.154232 | 2.96886 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1001.55 | 0.514259 | 6274.55ms | 65103 | 640 | 6.50433e+07 | 61991.1 | 0.102983 | 3.03266 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 993.681 | 0.195226 | 6456.5ms | 65103 | 4890 | 7.27599e+07 | 62481.9 | 1.11906 | 3.05717 | 2(Tie) | true |
| simdjson (ondemand) | 807.856 | 0.171825 | 7682.92ms | 65103 | 1280 | 2.23212e+07 | 76854.1 | 0.0703964 | 3.76105 | 4(Loss) | true |
