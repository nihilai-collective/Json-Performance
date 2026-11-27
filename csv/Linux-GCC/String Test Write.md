
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.33 | 0.0738823 | 242.812ms | 4215 | 160 | 521.305 | 2443.12 | 0.0399238 | 1.48712 | 1(Win) | true |
| simdjson (reflection) | 1529.77 | 0.0921114 | 270.155ms | 4215 | 30 | 175.747 | 2627.67 | 0.34134 | 1.60251 | 2(Loss) | true |
| Glaze | 961.208 | 0.48579 | 419.541ms | 4215 | 640 | 264142 | 4181.96 | 0.278604 | 2.55937 | 3(Loss) | true |
