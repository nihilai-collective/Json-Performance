
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.38 | 0.347619 | 6403.85ms | 94653 | 160 | 7.74329e+06 | 63284.9 | 0.227282 | 1.73502 | 1(Win) | true |
| simdjson (ondemand) | 1348.14 | 0.139012 | 6713.61ms | 94653 | 4890 | 4.23654e+07 | 66957.4 | 0.0817823 | 1.83575 | 2(Loss) | true |
