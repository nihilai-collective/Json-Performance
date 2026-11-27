
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1546.34 | 0.191355 | 3264.88ms | 53331 | 2560 | 1.01408e+07 | 32890.9 | 1.08178 | 1(Win) | true |
| Glaze | 1505.9 | 0.0974073 | 3570.15ms | 53331 | 2560 | 2.77071e+06 | 33774.1 | 0.978569 | 2(Loss) | true |
| Jsonifier (two-stage) | 1454.42 | 0.108753 | 3627.18ms | 53331 | 30 | 43389.4 | 34969.6 | 0.0732601 | 3(Loss) | true |
| simdjson (reflection) | 1035.99 | 0.227328 | 5070.61ms | 53331 | 4890 | 6.09067e+07 | 49093.5 | 1.97352 | 4(Loss) | true |
| simdjson (ondemand) | 911.722 | 0.382785 | 5577.48ms | 53331 | 1280 | 5.83653e+07 | 55785 | 0.35973 | 5(Loss) | true |
