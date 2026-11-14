
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2175.06 | 0.153336 | 3035.57ms | 53331 | 2560 | 3.29113e+06 | 23383.4 | 0.28305 | 1(Win) | true |
| Glaze | 1841.54 | 0.189034 | 3496.5ms | 53331 | 1280 | 3.48888e+06 | 27618.4 | 0.210447 | 2(Loss) | true |
| Jsonifier (two-stage) | 1731.03 | 0.186929 | 3587.53ms | 53331 | 1280 | 3.86111e+06 | 29381.6 | 0.062585 | 3(Loss) | true |
| simdjson (reflection) | 1345.44 | 0.161813 | 4510.31ms | 53331 | 1280 | 4.78926e+06 | 37802.2 | 0.120243 | 4(Loss) | true |
| simdjson (ondemand) | 1128.05 | 0.0802771 | 5163.68ms | 53331 | 4890 | 6.40614e+06 | 45087 | 0.0733444 | 5(Loss) | true |
