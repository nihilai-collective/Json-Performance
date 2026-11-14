
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1480.33 | 0.159108 | 7728.57ms | 94653 | 4890 | 4.60304e+07 | 60978.5 | 0.132697 | 2.05189 | 1(Win) | true |
| Glaze | 1406.48 | 0.160766 | 8093.77ms | 94653 | 160 | 1.70337e+06 | 64180 | 0.0272596 | 2.15988 | 2(Loss) | true |
| Jsonifier (two-stage) | 1331.99 | 0.0344232 | 8445.67ms | 94653 | 4890 | 2.66122e+06 | 67769.6 | 0.0305013 | 2.28105 | 3(Loss) | true |
| simdjson (ondemand) | 1074.13 | 0.137121 | 5076.93ms | 94653 | 320 | 4.24927e+06 | 84038.4 | 0.0353386 | 2.82878 | 4(Loss) | true |
