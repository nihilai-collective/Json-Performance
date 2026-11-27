
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 859.97 | 0.188765 | 470.48ms | 4215 | 4890 | 380699 | 4674.28 | 0.125895 | 1(Win) | true |
| simdjson (reflection) | 831.125 | 0.203208 | 498.434ms | 4215 | 2560 | 247276 | 4836.5 | 0.307128 | 2(Loss) | true |
| Glaze | 554.844 | 0.496174 | 788.508ms | 4215 | 160 | 206748 | 7244.8 | 0.132685 | 3(Loss) | true |
