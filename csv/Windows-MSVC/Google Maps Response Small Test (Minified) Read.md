
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1139.61 | 0.27282 | 380.666ms | 4390 | 80 | 8036.39 | 3673.75 | 1.11036 | 2.65368 | 1(Win) | true |
| Jsonifier (two-stage) | 976.901 | 0.135426 | 449.578ms | 4390 | 160 | 5389.54 | 4285.62 | 0.808586 | 3.10043 | 2(Loss) | true |
| Glaze | 878.982 | 0.43817 | 489.302ms | 4390 | 4890 | 2.12993e+06 | 4763.05 | 0.0377077 | 3.44282 | 3(Loss) | true |
| simdjson (ondemand) | 598.625 | 0.403256 | 749.549ms | 4390 | 80 | 63631.3 | 6993.75 | 2.18531 | 5.06462 | 4(Loss) | true |
