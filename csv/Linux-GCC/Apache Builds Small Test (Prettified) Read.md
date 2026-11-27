
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2510.96 | 0.21628 | 131.516ms | 3370 | 4890 | 37473.2 | 1279.94 | 0.230461 | 0.96498 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2374.51 | 0.338731 | 140.081ms | 3370 | 2560 | 53809.7 | 1353.49 | 0.553124 | 1.02053 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2362.46 | 0.320562 | 139.904ms | 3370 | 4890 | 92995.8 | 1360.4 | 0.465444 | 1.02724 | 2(Tie) | true |
| simdjson (ondemand) | 2079.4 | 0.105422 | 159.534ms | 3370 | 160 | 424.786 | 1545.58 | 0.00606531 | 1.16945 | 4(Loss) | true |
| Glaze | 1965.08 | 0.121361 | 161.032ms | 3370 | 30 | 118.19 | 1635.5 | 0.294656 | 1.24054 | 5(Loss) | true |
