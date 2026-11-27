
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2221.62 | 0.543537 | 323.908ms | 6701 | 640 | 156451 | 2876.54 | 0.69771 | 1.10374 | 1(Win) | true |
| Jsonifier (two-stage) | 2122.27 | 0.284877 | 306.722ms | 6701 | 1280 | 94189.5 | 3011.2 | 0.170801 | 1.15613 | 2(Loss) | true |
| simdjson (reflection) | 2059.18 | 0.178878 | 322.36ms | 6701 | 40 | 1232.72 | 3103.45 | 0.0488465 | 1.19116 | 3(Loss) | true |
| Glaze | 1819.74 | 0.478929 | 353.399ms | 6701 | 320 | 90521.4 | 3511.8 | 0.744915 | 1.34991 | 4(Loss) | true |
| simdjson (ondemand) | 1785.02 | 0.220885 | 362.705ms | 6701 | 4890 | 305799 | 3580.12 | 0.260401 | 1.37672 | 5(Loss) | true |
