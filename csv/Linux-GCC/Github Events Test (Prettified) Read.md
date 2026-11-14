
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1890.26 | 0.076472 | 4008.26ms | 65103 | 640 | 403779 | 32845.8 | 0.0210212 | 2.69519 | 9.14603 | 1.56905 | 0.00956993 | 8.18655e-05 | 6.50412e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1877.54 | 0.0277302 | 4040.35ms | 65103 | 4890 | 411186 | 33068.3 | 0.0591732 | 2.72462 | 9.1684 | 1.4953 | 0.00942755 | 3.17383e-05 | 2.12185e-05 | 2(Loss) | true |
| Jsonifier | 1712.56 | 0.0396649 | 4368.79ms | 65103 | 1280 | 264688 | 36254 | 0.125832 | 2.99686 | 9.2139 | 1.68492 | 0.00902756 | 7.22533e-05 | 6.05051e-05 | 3(Loss) | true |
| Glaze | 1683.09 | 0.045509 | 4433.22ms | 65103 | 2560 | 721471 | 36888.6 | 0.109614 | 3.04789 | 10.7766 | 2.11952 | 0.0126895 | 2.92385e-05 | 2.05024e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1617.77 | 0.0938311 | 4611.97ms | 65103 | 160 | 207482 | 38378.1 | 0.0320556 | 3.18513 | 9.4824 | 1.72497 | 0.0107073 | 3.28326e-05 | 2.20804e-05 | 5(Loss) | true |
