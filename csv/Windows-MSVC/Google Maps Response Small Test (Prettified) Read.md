
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2082.32 | 0.262967 | 441.157ms | 9378 | 40 | 5102.56 | 4295 | 0.0388199 | 1.4478 | 1(Win) | true |
| Jsonifier (two-stage) | 1980.58 | 0.144857 | 454.885ms | 9378 | 1280 | 54767.4 | 4515.62 | 0.329804 | 1.52747 | 2(Loss) | true |
| Glaze | 1422.82 | 0.130691 | 656.194ms | 9378 | 1280 | 86380.9 | 6285.78 | 1.63578 | 2.12933 | 3(Loss) | true |
| simdjson (ondemand) | 1217.59 | 0.115952 | 747.053ms | 9378 | 640 | 46425.6 | 7345.31 | 0.110737 | 2.4888 | 4(Loss) | true |
