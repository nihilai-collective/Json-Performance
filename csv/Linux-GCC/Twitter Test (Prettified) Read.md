
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 19983.8 | 0.0543891 | 3087.51ms | 631514 | 4890 | 1.31384e+06 | 30137.3 | 0.211125 | 0.123777 | 1(Win) | true |
| simdjson (stage-1) | 17090.1 | 0.0795892 | 3611.09ms | 631514 | 1280 | 1.00692e+06 | 35240.2 | 0.135163 | 0.144721 | 2(Loss) | true |
