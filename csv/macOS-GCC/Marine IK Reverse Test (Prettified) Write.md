
----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6184.42 | 0.685221 | 9707.32ms | 10018896 | 160 | 1.79318e+10 | 1.54497e+06 | 0.129595 | 1(Win) | true |
| Glaze | 3300.64 | 0.40871 | 9165.63ms | 9930228 | 30 | 4.12548e+09 | 2.86921e+06 | 0.201753 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 290.094 | 0.468564 | 10018.3ms | 10018896 | 30 | 7.14533e+11 | 3.29368e+07 | 7.76898 | -(Loss) | false |
