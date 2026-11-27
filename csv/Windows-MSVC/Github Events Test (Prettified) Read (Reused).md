
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1663.66 | 0.730196 | 4590.33ms | 65103 | 4890 | 3.6313e+08 | 37319.6 | 0.244845 | 1.82524 | 1(Win) | true |
| Glaze | 1601.17 | 1.42014 | 4656.09ms | 65103 | 1280 | 3.88151e+08 | 38776 | 0.04132 | 1.89666 | 2(Loss) | true |
| Jsonifier (two-stage) | 1476.85 | 0.771863 | 5011.06ms | 65103 | 4890 | 5.14896e+08 | 42040.2 | 0.35454 | 2.05656 | 3(Loss) | true |
| simdjson (ondemand) | 1168.68 | 0.176923 | 6012.85ms | 65103 | 4890 | 4.32006e+07 | 53126 | 0.100715 | 2.59926 | 4(Loss) | true |
