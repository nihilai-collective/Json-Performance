
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2287.11 | 0.520221 | 1099.96ms | 25388 | 320 | 970531 | 10586.2 | 0.0118064 | 1.32717 | 1(Win) | true |
| Jsonifier (two-stage) | 2183.06 | 0.0504032 | 1114.21ms | 25388 | 4890 | 152810 | 11090.8 | 0.045971 | 1.38883 | 2(Loss) | true |
| Glaze | 1466.22 | 0.206015 | 1671.57ms | 25388 | 160 | 185173 | 16513.1 | 0.147392 | 2.07014 | 3(Loss) | true |
| simdjson (ondemand) | 1239.74 | 0.14276 | 1977.85ms | 25388 | 640 | 497496 | 19529.8 | 0.0744608 | 2.4493 | 4(Loss) | true |
