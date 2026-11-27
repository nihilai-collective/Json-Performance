
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 21254.6 | 0.145162 | 295.912ms | 65103 | 4890 | 87924.7 | 2921.11 | 0.0580848 | 0.115429 | 1(Win) | true |
| simdjson (stage-1) | 18100.4 | 0.0212143 | 347.585ms | 65103 | 160 | 84.7239 | 3430.16 | 0.0432018 | 0.135721 | 2(Loss) | true |
