
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1748.34 | 0.0993686 | 4246.18ms | 65103 | 4890 | 6.08916e+06 | 35512 | 0.144076 | 1.41485 | 1(Win) | true |
| Glaze | 1621.29 | 0.125112 | 4577.49ms | 65103 | 2560 | 5.87646e+06 | 38294.8 | 0.0937562 | 1.52601 | 2(Loss) | true |
| Jsonifier | 1499.81 | 0.175529 | 4887.44ms | 65103 | 2560 | 1.35165e+07 | 41396.5 | 0.031224 | 1.64964 | 3(Loss) | true |
| simdjson (ondemand) | 954.442 | 0.303971 | 7219.33ms | 65103 | 160 | 6.25585e+06 | 65050.6 | 0.235949 | 2.59308 | 4(Loss) | true |
