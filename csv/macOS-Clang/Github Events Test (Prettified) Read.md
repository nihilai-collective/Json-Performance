
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) DID NOT CONVERGE | 7559.53 | 0.273712 | 809.933ms | 65103 | 4890 | 2.4712e+06 | 8213.08 | 7.01026 | -(Win) | false |
| simdjson (stage-1) | 7294.06 | 0.267505 | 872.386ms | 65103 | 4890 | 2.53534e+06 | 8512.01 | 0.850185 | 2(Loss) | true |
