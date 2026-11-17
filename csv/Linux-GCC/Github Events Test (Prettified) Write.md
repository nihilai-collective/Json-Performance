
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18593.7 | 0.0451008 | 409.452ms | 78778 | 160 | 531.332 | 4040.53 | 0.00262954 | 0.132245 | 1(Win) | true |
| Glaze | 5238.43 | 0.205778 | 1438.78ms | 78778 | 1280 | 1.11485e+06 | 14341.8 | 0.360143 | 0.47173 | 2(Loss) | true |
| simdjson (reflection) | 657.608 | 0.368156 | 5955.75ms | 78778 | 80 | 1.41524e+07 | 114245 | 0.230859 | 3.76342 | 3(Loss) | true |
