
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1458.12 | 0.0257088 | 4418.63ms | 56369 | 2560 | 229985 | 36867.8 | 0.0232631 | 3.5028 | 15.0917 | 2.97506 | 0.00730767 | 3.17661e-05 | 1.86688e-05 | 1(Win) | true |
| simdjson (ondemand) | 1285.6 | 0.0233886 | 4914.31ms | 56369 | 2560 | 244859 | 41815.2 | 0.0580641 | 3.98395 | 15.7498 | 2.78775 | 0.00980135 | 1.33953e-05 | 3.88068e-06 | 2(Loss) | true |
