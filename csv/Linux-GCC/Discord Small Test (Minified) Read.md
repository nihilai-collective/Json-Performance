
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2355.2 | 0.0802141 | 917.633ms | 4857 | 2560 | 6371.18 | 1966.71 | 0.309421 | 2.22561 | 8.76385 | 1.60984 | 0.000247066 | 7.33477e-05 | 3.95692e-05 | 1(Win) | true |
| Glaze | 1810.81 | 0.199632 | 974.395ms | 4857 | 320 | 8344.51 | 2557.97 | 0.0488908 | 2.88798 | 11.344 | 2.24017 | 0.00091556 | 6.30533e-05 | 1.22246e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1665.36 | 0.053691 | 1001.28ms | 4857 | 2560 | 5709.06 | 2781.38 | 0.124684 | 3.1597 | 12.6866 | 2.06547 | 0.00106933 | 0.000101738 | 4.75313e-05 | 3(Loss) | true |
| simdjson (reflection) | 1576.65 | 0.0974021 | 1018.83ms | 4857 | 160 | 1310.15 | 2937.87 | 0.0639935 | 3.3134 | 12.8328 | 2.14947 | 0.000832561 | 4.50381e-05 | 1.67284e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1306.13 | 0.0657232 | 1077.12ms | 4857 | 2560 | 13907.1 | 3546.34 | 0.0635485 | 3.98812 | 14.3214 | 2.68293 | 0.00141693 | 0.000106483 | 5.51717e-05 | 5(Loss) | true |
