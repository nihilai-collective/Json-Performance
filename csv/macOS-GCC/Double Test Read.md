
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 967.24 | 1.05431 | 199.608ms | 1811 | 640 | 226822 | 1785.6 | 2.14818 | 1(Win) | true |
| Glaze | 920.141 | 0.454527 | 193.209ms | 1811 | 2560 | 186333 | 1877 | 0.656293 | 2(Loss) | true |
| simdjson (ondemand) | 298.848 | 1.24775 | 661.851ms | 1811 | 40 | 207993 | 5779.2 | 0.257732 | 3(Loss) | true |
| simdjson (reflection) | 273.761 | 0.674373 | 666.333ms | 1811 | 320 | 579221 | 6308.8 | 0.433011 | 4(Loss) | true |
