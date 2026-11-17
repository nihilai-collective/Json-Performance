
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 704.001 | 1.07871 | 732.041ms | 4604 | 80 | 362097 | 6236.8 | 0.257202 | 1(Win) | true |
| simdjson (reflection) | 513.792 | 0.223349 | 867.632ms | 4604 | 2560 | 932617 | 8545.7 | 0.566648 | 2(Loss) | true |
| Jsonifier (two-stage) | 479.189 | 0.382937 | 907.499ms | 4604 | 1280 | 1.57587e+06 | 9162.8 | 1.02761 | 3(Loss) | true |
| Glaze | 424.257 | 0.165757 | 1067.16ms | 4604 | 2560 | 753349 | 10349.2 | 0.110275 | 4(Loss) | true |
| simdjson (ondemand) | 372.745 | 0.125757 | 1191.66ms | 4604 | 4890 | 1.07305e+06 | 11779.4 | 0.356949 | 5(Loss) | true |
