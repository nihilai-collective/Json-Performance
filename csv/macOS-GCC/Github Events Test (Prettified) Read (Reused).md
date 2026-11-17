
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2146.02 | 0.709284 | 3804.43ms | 65103 | 160 | 6.73742e+06 | 28931.2 | 0.814005 | 1(Win) | true |
| Glaze | 1928.39 | 0.298968 | 4122.07ms | 65103 | 640 | 5.92986e+06 | 32196.4 | 2.09575 | 2(Loss) | true |
| Jsonifier (two-stage) | 1672.3 | 0.703209 | 4320.91ms | 65103 | 640 | 4.36239e+07 | 37126.8 | 1.14704 | 3(Loss) | true |
| simdjson (reflection) | 1540.13 | 0.709711 | 5108.34ms | 65103 | 640 | 5.23877e+07 | 40312.8 | 0.376479 | 4(Loss) | true |
| simdjson (ondemand) | 1176.51 | 0.262117 | 5931.15ms | 65103 | 4890 | 9.35635e+07 | 52772.1 | 0.335332 | 5(Loss) | true |
