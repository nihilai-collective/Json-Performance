
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 757.271 | 0.194187 | 8868.32ms | 2251027 | 160 | 4.84862e+09 | 2.83484e+06 | 0.300941 | 1(Win) | true |
| Glaze | 651.639 | 0.072995 | 10404.9ms | 2251027 | 40 | 2.3131e+08 | 3.29438e+06 | 0.505064 | 2(Loss) | true |
| simdjson (reflection) | 641.636 | 0.296789 | 5118.66ms | 2251027 | 80 | 7.88803e+09 | 3.34574e+06 | 0.405543 | 3(Loss) | true |
| Jsonifier (two-stage) | 624.568 | 0.0796616 | 5254.61ms | 2251027 | 40 | 2.99889e+08 | 3.43717e+06 | 0.171134 | 4(Loss) | true |
| simdjson (ondemand) | 575.082 | 0.598782 | 5712.52ms | 2251027 | 80 | 3.99696e+10 | 3.73294e+06 | 2.26814 | 5(Loss) | true |
